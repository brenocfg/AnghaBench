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
struct TYPE_3__ {int size; int limit; int /*<<< orphan*/  table; scalar_t__ used; } ;
typedef  TYPE_1__ hashtable ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 int /*<<< orphan*/  BDF_Err_Ok ; 
 scalar_t__ FT_NEW_ARRAY (int /*<<< orphan*/ ,int) ; 
 int INITIAL_HT_SIZE ; 

__attribute__((used)) static FT_Error
  hash_init( hashtable*  ht,
             FT_Memory   memory )
  {
    int       sz = INITIAL_HT_SIZE;
    FT_Error  error = BDF_Err_Ok;


    ht->size  = sz;
    ht->limit = sz / 3;
    ht->used  = 0;

    if ( FT_NEW_ARRAY( ht->table, sz ) )
      goto Exit;

  Exit:
    return error;
  }