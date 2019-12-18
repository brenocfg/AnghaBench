#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  org_len; int /*<<< orphan*/  org_pos; } ;
struct TYPE_17__ {int max_hints; int num_hints; TYPE_1__* hint_masks; TYPE_5__* hints; int /*<<< orphan*/ * zone; scalar_t__ num_zones; TYPE_5__* sort; TYPE_5__* sort_global; TYPE_5__* zones; } ;
struct TYPE_16__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  len; int /*<<< orphan*/  pos; } ;
struct TYPE_15__ {int num_hints; TYPE_3__* hints; } ;
struct TYPE_14__ {int num_masks; int /*<<< orphan*/  masks; } ;
typedef  TYPE_1__* PS_Mask_Table ;
typedef  int /*<<< orphan*/  PS_Mask ;
typedef  TYPE_2__* PS_Hint_Table ;
typedef  TYPE_3__* PS_Hint ;
typedef  TYPE_4__* PSH_Hint_Table ;
typedef  TYPE_5__* PSH_Hint ;
typedef  int FT_UInt ;
typedef  int /*<<< orphan*/  FT_Memory ;
typedef  int /*<<< orphan*/  FT_Error ;

/* Variables and functions */
 scalar_t__ FT_NEW_ARRAY (TYPE_5__*,int) ; 
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  FT_UNUSED (TYPE_1__*) ; 
 int /*<<< orphan*/  psh_hint_table_record (TYPE_4__*,int) ; 
 int /*<<< orphan*/  psh_hint_table_record_mask (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static FT_Error
  psh_hint_table_init( PSH_Hint_Table  table,
                       PS_Hint_Table   hints,
                       PS_Mask_Table   hint_masks,
                       PS_Mask_Table   counter_masks,
                       FT_Memory       memory )
  {
    FT_UInt   count;
    FT_Error  error;

    FT_UNUSED( counter_masks );


    count = hints->num_hints;

    /* allocate our tables */
    if ( FT_NEW_ARRAY( table->sort,  2 * count     ) ||
         FT_NEW_ARRAY( table->hints,     count     ) ||
         FT_NEW_ARRAY( table->zones, 2 * count + 1 ) )
      goto Exit;

    table->max_hints   = count;
    table->sort_global = table->sort + count;
    table->num_hints   = 0;
    table->num_zones   = 0;
    table->zone        = NULL;

    /* initialize the `table->hints' array */
    {
      PSH_Hint  write = table->hints;
      PS_Hint   read  = hints->hints;


      for ( ; count > 0; count--, write++, read++ )
      {
        write->org_pos = read->pos;
        write->org_len = read->len;
        write->flags   = read->flags;
      }
    }

    /* we now need to determine the initial `parent' stems; first  */
    /* activate the hints that are given by the initial hint masks */
    if ( hint_masks )
    {
      PS_Mask  mask = hint_masks->masks;


      count             = hint_masks->num_masks;
      table->hint_masks = hint_masks;

      for ( ; count > 0; count--, mask++ )
        psh_hint_table_record_mask( table, mask );
    }

    /* finally, do a linear parse in case some hints were left alone */
    if ( table->num_hints != table->max_hints )
    {
      FT_UInt  idx;


      FT_TRACE0(( "psh_hint_table_init: missing/incorrect hint masks\n" ));

      count = table->max_hints;
      for ( idx = 0; idx < count; idx++ )
        psh_hint_table_record( table, idx );
    }

  Exit:
    return error;
  }