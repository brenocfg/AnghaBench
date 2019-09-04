#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {scalar_t__ org_pos; } ;
struct TYPE_10__ {size_t max_hints; size_t num_hints; TYPE_3__** sort; TYPE_3__* hints; } ;
struct TYPE_9__ {size_t num_bits; int /*<<< orphan*/ * bytes; } ;
typedef  TYPE_1__* PS_Mask ;
typedef  TYPE_2__* PSH_Hint_Table ;
typedef  TYPE_3__* PSH_Hint ;
typedef  size_t FT_UInt ;
typedef  int FT_Int ;
typedef  int /*<<< orphan*/  FT_Byte ;

/* Variables and functions */
 int /*<<< orphan*/  FT_TRACE0 (char*) ; 
 int /*<<< orphan*/  psh_hint_activate (TYPE_3__*) ; 
 int /*<<< orphan*/  psh_hint_is_active (TYPE_3__*) ; 
 int /*<<< orphan*/  psh_hint_table_deactivate (TYPE_2__*) ; 

__attribute__((used)) static void
  psh_hint_table_activate_mask( PSH_Hint_Table  table,
                                PS_Mask         hint_mask )
  {
    FT_Int    mask = 0, val = 0;
    FT_Byte*  cursor = hint_mask->bytes;
    FT_UInt   idx, limit, count;


    limit = hint_mask->num_bits;
    count = 0;

    psh_hint_table_deactivate( table );

    for ( idx = 0; idx < limit; idx++ )
    {
      if ( mask == 0 )
      {
        val  = *cursor++;
        mask = 0x80;
      }

      if ( val & mask )
      {
        PSH_Hint  hint = &table->hints[idx];


        if ( !psh_hint_is_active( hint ) )
        {
          FT_UInt     count2;

#if 0
          PSH_Hint*  sort = table->sort;
          PSH_Hint   hint2;


          for ( count2 = count; count2 > 0; count2--, sort++ )
          {
            hint2 = sort[0];
            if ( psh_hint_overlap( hint, hint2 ) )
              FT_TRACE0(( "psh_hint_table_activate_mask:"
                          " found overlapping hints\n" ))
          }
#else
          count2 = 0;
#endif

          if ( count2 == 0 )
          {
            psh_hint_activate( hint );
            if ( count < table->max_hints )
              table->sort[count++] = hint;
            else
              FT_TRACE0(( "psh_hint_tableactivate_mask:"
                          " too many active hints\n" ));
          }
        }
      }

      mask >>= 1;
    }
    table->num_hints = count;

    /* now, sort the hints; they are guaranteed to not overlap */
    /* so we can compare their "org_pos" field directly        */
    {
      FT_Int     i1, i2;
      PSH_Hint   hint1, hint2;
      PSH_Hint*  sort = table->sort;


      /* a simple bubble sort will do, since in 99% of cases, the hints */
      /* will be already sorted -- and the sort will be linear          */
      for ( i1 = 1; i1 < (FT_Int)count; i1++ )
      {
        hint1 = sort[i1];
        for ( i2 = i1 - 1; i2 >= 0; i2-- )
        {
          hint2 = sort[i2];

          if ( hint2->org_pos < hint1->org_pos )
            break;

          sort[i2 + 1] = hint2;
          sort[i2]     = hint1;
        }
      }
    }
  }