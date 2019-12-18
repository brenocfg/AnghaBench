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
typedef  int /*<<< orphan*/  text ;
typedef  int /*<<< orphan*/  int64 ;
typedef  int /*<<< orphan*/  Datum ;

/* Variables and functions */
 int /*<<< orphan*/  DatumGetInt64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PointerGetDatum (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cstring_to_text (char*) ; 
 int /*<<< orphan*/  master_create_empty_shard ; 

__attribute__((used)) static int64
CreateEmptyShard(char *relationName)
{
	int64 shardId = 0;

	text *relationNameText = cstring_to_text(relationName);
	Datum relationNameDatum = PointerGetDatum(relationNameText);
	Datum shardIdDatum = DirectFunctionCall1(master_create_empty_shard,
											 relationNameDatum);
	shardId = DatumGetInt64(shardIdDatum);

	return shardId;
}