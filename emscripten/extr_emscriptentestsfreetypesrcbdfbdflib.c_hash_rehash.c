#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int size; int limit; TYPE_2__** table; } ;
typedef  TYPE_1__ hashtable ;
typedef  TYPE_2__* hashnode ;
struct TYPE_9__ {int /*<<< orphan*/  key; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  BDF_Err_Ok ; 
 int /*<<< orphan*/  FT_FREE (TYPE_2__**) ; 
 scalar_t__ FT_NEW_ARRAY (TYPE_2__**,int) ; 
 TYPE_2__** hash_bucket (int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static FT_Error
  hash_rehash( hashtable*  ht,
               FT_Memory   memory )
  {
    hashnode*  obp = ht->table, *bp, *nbp;
    int        i, sz = ht->size;
    FT_Error   error = BDF_Err_Ok;


    ht->size <<= 1;
    ht->limit  = ht->size / 3;

    if ( FT_NEW_ARRAY( ht->table, ht->size ) )
      goto Exit;

    for ( i = 0, bp = obp; i < sz; i++, bp++ )
    {
      if ( *bp )
      {
        nbp = hash_bucket( (*bp)->key, ht );
        *nbp = *bp;
      }
    }
    FT_FREE( obp );

  Exit:
    return error;
  }