#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ALLOCSET_DEFAULT_SIZES ; 
 int /*<<< orphan*/ * AllocSetContextCreate (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * CacheMemoryContext ; 
 int /*<<< orphan*/  CreateCacheMemoryContext () ; 
 int /*<<< orphan*/ * DistShardCacheHash ; 
 int /*<<< orphan*/ * DistTableCacheHash ; 
 int /*<<< orphan*/  InitializeDistCache () ; 
 int /*<<< orphan*/  MemoryContextDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * MetadataCacheMemoryContext ; 
 int /*<<< orphan*/  PG_CATCH () ; 
 int /*<<< orphan*/  PG_END_TRY () ; 
 int /*<<< orphan*/  PG_RE_THROW () ; 
 int /*<<< orphan*/  PG_TRY () ; 
 int /*<<< orphan*/  RegisterForeignKeyGraphCacheCallbacks () ; 
 int /*<<< orphan*/  RegisterLocalGroupIdCacheCallbacks () ; 
 int /*<<< orphan*/  RegisterWorkerNodeCacheCallbacks () ; 

__attribute__((used)) static void
InitializeCaches(void)
{
	static bool performedInitialization = false;

	if (!performedInitialization)
	{
		MetadataCacheMemoryContext = NULL;

		/*
		 * If either of dist table cache or shard cache
		 * allocation and initializations fail due to an exception
		 * that is caused by OOM or any other reason,
		 * we reset the flag, and delete the shard cache memory
		 * context to reclaim partially allocated memory.
		 *
		 * Command will continue to fail since we re-throw the exception.
		 */
		PG_TRY();
		{
			/* set first, to avoid recursion dangers */
			performedInitialization = true;

			/* make sure we've initialized CacheMemoryContext */
			if (CacheMemoryContext == NULL)
			{
				CreateCacheMemoryContext();
			}

			MetadataCacheMemoryContext = AllocSetContextCreate(
				CacheMemoryContext,
				"MetadataCacheMemoryContext",
				ALLOCSET_DEFAULT_SIZES);

			InitializeDistCache();
			RegisterForeignKeyGraphCacheCallbacks();
			RegisterWorkerNodeCacheCallbacks();
			RegisterLocalGroupIdCacheCallbacks();
		}
		PG_CATCH();
		{
			performedInitialization = false;

			if (MetadataCacheMemoryContext != NULL)
			{
				MemoryContextDelete(MetadataCacheMemoryContext);
			}

			MetadataCacheMemoryContext = NULL;
			DistTableCacheHash = NULL;
			DistShardCacheHash = NULL;

			PG_RE_THROW();
		}
		PG_END_TRY();
	}
}