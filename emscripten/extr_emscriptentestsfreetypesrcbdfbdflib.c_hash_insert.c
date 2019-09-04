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
struct TYPE_8__ {scalar_t__ used; scalar_t__ limit; } ;
typedef  TYPE_1__ hashtable ;
typedef  TYPE_2__* hashnode ;
struct TYPE_9__ {char* key; size_t data; } ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ BDF_Err_Ok ; 
 scalar_t__ FT_NEW (TYPE_2__*) ; 
 TYPE_2__** hash_bucket (char*,TYPE_1__*) ; 
 scalar_t__ hash_rehash (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  hash_insert( char*       key,
               size_t      data,
               hashtable*  ht,
               FT_Memory   memory )
  {
    hashnode  nn, *bp = hash_bucket( key, ht );
    FT_Error  error = BDF_Err_Ok;


    nn = *bp;
    if ( !nn )
    {
      if ( FT_NEW( nn ) )
        goto Exit;
      *bp = nn;

      nn->key  = key;
      nn->data = data;

      if ( ht->used >= ht->limit )
      {
        error = hash_rehash( ht, memory );
        if ( error )
          goto Exit;
      }
      ht->used++;
    }
    else
      nn->data = data;

  Exit:
    return error;
  }