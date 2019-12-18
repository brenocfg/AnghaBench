#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  optdata; } ;
struct TYPE_8__ {TYPE_1__ statetable; } ;
struct TYPE_7__ {int /*<<< orphan*/  valueTable_length; int /*<<< orphan*/  valueTable; } ;
typedef  TYPE_2__* GXV_kern_fmt1_StateOptRecData ;
typedef  TYPE_3__* GXV_Validator ;
typedef  int /*<<< orphan*/  FT_UShort ;

/* Variables and functions */
 int /*<<< orphan*/  gxv_set_length_by_ushort_offset (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,TYPE_3__*) ; 

__attribute__((used)) static void
  gxv_kern_subtable_fmt1_subtable_setup( FT_UShort      table_size,
                                         FT_UShort      classTable,
                                         FT_UShort      stateArray,
                                         FT_UShort      entryTable,
                                         FT_UShort*     classTable_length_p,
                                         FT_UShort*     stateArray_length_p,
                                         FT_UShort*     entryTable_length_p,
                                         GXV_Validator  gxvalid )
  {
    FT_UShort  o[4];
    FT_UShort  *l[4];
    FT_UShort  buff[5];

    GXV_kern_fmt1_StateOptRecData  optdata =
      (GXV_kern_fmt1_StateOptRecData)gxvalid->statetable.optdata;


    o[0] = classTable;
    o[1] = stateArray;
    o[2] = entryTable;
    o[3] = optdata->valueTable;
    l[0] = classTable_length_p;
    l[1] = stateArray_length_p;
    l[2] = entryTable_length_p;
    l[3] = &(optdata->valueTable_length);

    gxv_set_length_by_ushort_offset( o, l, buff, 4, table_size, gxvalid );
  }