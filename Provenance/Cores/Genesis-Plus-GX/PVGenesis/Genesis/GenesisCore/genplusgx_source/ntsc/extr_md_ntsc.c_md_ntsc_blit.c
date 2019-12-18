#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  md_ntsc_t ;
typedef  int /*<<< orphan*/  md_ntsc_out_t ;
struct TYPE_2__ {int pitch; int /*<<< orphan*/ * data; } ;
typedef  int /*<<< orphan*/  MD_NTSC_IN_T ;

/* Variables and functions */
 int /*<<< orphan*/  MD_NTSC_ADJ_IN (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  MD_NTSC_BEGIN_ROW (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD_NTSC_COLOR_IN (int,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MD_NTSC_RGB_OUT (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ bitmap ; 
 int md_ntsc_in_chunk ; 

void md_ntsc_blit( md_ntsc_t const* ntsc, MD_NTSC_IN_T const* table, unsigned char* input,
                   int in_width, int vline)
{
  int const chunk_count = in_width / md_ntsc_in_chunk - 1;

  /* use palette entry 0 for unused pixels */
  MD_NTSC_IN_T border = table[0];

  MD_NTSC_BEGIN_ROW( ntsc, border,
        MD_NTSC_ADJ_IN( table[*input++] ),
        MD_NTSC_ADJ_IN( table[*input++] ),
        MD_NTSC_ADJ_IN( table[*input++] ) );

  md_ntsc_out_t* restrict line_out  = (md_ntsc_out_t*)(&bitmap.data[(vline * bitmap.pitch)]);

  int n;

  for ( n = chunk_count; n; --n )
  {
    /* order of input and output pixels must not be altered */
    MD_NTSC_COLOR_IN( 0, ntsc, MD_NTSC_ADJ_IN( table[*input++] ) );
    MD_NTSC_RGB_OUT( 0, *line_out++ );
    MD_NTSC_RGB_OUT( 1, *line_out++ );

    MD_NTSC_COLOR_IN( 1, ntsc, MD_NTSC_ADJ_IN( table[*input++] ) );
    MD_NTSC_RGB_OUT( 2, *line_out++ );
    MD_NTSC_RGB_OUT( 3, *line_out++ );

    MD_NTSC_COLOR_IN( 2, ntsc, MD_NTSC_ADJ_IN( table[*input++] ) );
    MD_NTSC_RGB_OUT( 4, *line_out++ );
    MD_NTSC_RGB_OUT( 5, *line_out++ );

    MD_NTSC_COLOR_IN( 3, ntsc, MD_NTSC_ADJ_IN( table[*input++] ) );
    MD_NTSC_RGB_OUT( 6, *line_out++ );
    MD_NTSC_RGB_OUT( 7, *line_out++ );
  }

  /* finish final pixels */
  MD_NTSC_COLOR_IN( 0, ntsc, MD_NTSC_ADJ_IN( table[*input++] ) );
  MD_NTSC_RGB_OUT( 0, *line_out++ );
  MD_NTSC_RGB_OUT( 1, *line_out++ );

  MD_NTSC_COLOR_IN( 1, ntsc, border );
  MD_NTSC_RGB_OUT( 2, *line_out++ );
  MD_NTSC_RGB_OUT( 3, *line_out++ );

  MD_NTSC_COLOR_IN( 2, ntsc, border );
  MD_NTSC_RGB_OUT( 4, *line_out++ );
  MD_NTSC_RGB_OUT( 5, *line_out++ );

  MD_NTSC_COLOR_IN( 3, ntsc, border );
  MD_NTSC_RGB_OUT( 6, *line_out++ );
  MD_NTSC_RGB_OUT( 7, *line_out++ );
}