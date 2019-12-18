#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int xMin; int yMin; int xMax; int yMax; } ;
struct TYPE_9__ {int Ascender; int Descender; int NumTrackKern; scalar_t__ TrackKerns; int NumKernPair; scalar_t__ KernPairs; TYPE_1__ FontBBox; scalar_t__ IsCIDFont; } ;
struct TYPE_8__ {int index1; int index2; int x; int y; } ;
struct TYPE_7__ {int degree; int min_ptsize; int min_kern; int max_ptsize; int max_kern; } ;
typedef  scalar_t__ FT_UInt ;
typedef  TYPE_2__* AFM_TrackKern ;
typedef  TYPE_3__* AFM_KernPair ;
typedef  TYPE_4__* AFM_FontInfo ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,...) ; 

void dump_fontinfo( AFM_FontInfo  fi )
  {
    FT_UInt  i;


    printf( "This AFM is for %sCID font.\n\n",
            ( fi->IsCIDFont ) ? "" : "non-" );

    printf( "FontBBox: %.2f %.2f %.2f %.2f\n", fi->FontBBox.xMin / 65536.,
                                               fi->FontBBox.yMin / 65536.,
                                               fi->FontBBox.xMax / 65536.,
                                               fi->FontBBox.yMax / 65536. );
    printf( "Ascender: %.2f\n", fi->Ascender / 65536. );
    printf( "Descender: %.2f\n\n", fi->Descender / 65536. );

    if ( fi->NumTrackKern )
      printf( "There are %d sets of track kernings:\n",
              fi->NumTrackKern );
    else
      printf( "There is no track kerning.\n" );

    for ( i = 0; i < fi->NumTrackKern; i++ )
    {
      AFM_TrackKern  tk = fi->TrackKerns + i;


      printf( "\t%2d: %5.2f %5.2f %5.2f %5.2f\n", tk->degree,
                                                  tk->min_ptsize / 65536.,
                                                  tk->min_kern / 65536.,
                                                  tk->max_ptsize / 65536.,
                                                  tk->max_kern / 65536. );
    }

    printf( "\n" );

    if ( fi->NumKernPair )
      printf( "There are %d kerning pairs:\n",
              fi->NumKernPair );
    else
      printf( "There is no kerning pair.\n" );

    for ( i = 0; i < fi->NumKernPair; i++ )
    {
      AFM_KernPair  kp = fi->KernPairs + i;


      printf( "\t%3d + %3d => (%4d, %4d)\n", kp->index1,
                                             kp->index2,
                                             kp->x,
                                             kp->y );
    }

  }