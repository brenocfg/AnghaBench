#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int size; int limit; int /*<<< orphan*/  table; int /*<<< orphan*/  compare; int /*<<< orphan*/  lookup; scalar_t__ used; } ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  TYPE_1__* FT_Hash ;
typedef  int /*<<< orphan*/  FT_Error ;
typedef  scalar_t__ FT_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  FT_MEM_NEW_ARRAY (int /*<<< orphan*/ ,int) ; 
 int INITIAL_HT_SIZE ; 
 int /*<<< orphan*/  hash_num_compare ; 
 int /*<<< orphan*/  hash_num_lookup ; 
 int /*<<< orphan*/  hash_str_compare ; 
 int /*<<< orphan*/  hash_str_lookup ; 

__attribute__((used)) static FT_Error
  hash_init( FT_Hash    hash,
             FT_Bool    is_num,
             FT_Memory  memory )
  {
    FT_UInt   sz = INITIAL_HT_SIZE;
    FT_Error  error;


    hash->size  = sz;
    hash->limit = sz / 3;
    hash->used  = 0;

    if ( is_num )
    {
      hash->lookup  = hash_num_lookup;
      hash->compare = hash_num_compare;
    }
    else
    {
      hash->lookup  = hash_str_lookup;
      hash->compare = hash_str_compare;
    }

    FT_MEM_NEW_ARRAY( hash->table, sz );

    return error;
  }