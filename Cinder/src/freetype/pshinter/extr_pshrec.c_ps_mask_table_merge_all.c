#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ num_masks; } ;
typedef  TYPE_1__* PS_Mask_Table ;
typedef  int /*<<< orphan*/  FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  scalar_t__ FT_Int ;
typedef  scalar_t__ FT_Error ;

/* Variables and functions */
 scalar_t__ FT_Err_Ok ; 
 scalar_t__ ps_mask_table_merge (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ps_mask_table_test_intersect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  ps_mask_table_merge_all( PS_Mask_Table  table,
                           FT_Memory      memory )
  {
    FT_Int    index1, index2;
    FT_Error  error = FT_Err_Ok;


    /* both loops go down to 0, thus FT_Int for index1 and index2 */
    for ( index1 = (FT_Int)table->num_masks - 1; index1 > 0; index1-- )
    {
      for ( index2 = index1 - 1; index2 >= 0; index2-- )
      {
        if ( ps_mask_table_test_intersect( table,
                                           (FT_UInt)index1,
                                           (FT_UInt)index2 ) )
        {
          error = ps_mask_table_merge( table,
                                       (FT_UInt)index2,
                                       (FT_UInt)index1,
                                       memory );
          if ( error )
            goto Exit;

          break;
        }
      }
    }

  Exit:
    return error;
  }