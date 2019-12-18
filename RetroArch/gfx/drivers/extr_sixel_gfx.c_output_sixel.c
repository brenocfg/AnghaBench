#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sixel_output_t ;
typedef  int /*<<< orphan*/  sixel_dither_t ;
typedef  int /*<<< orphan*/  SIXELSTATUS ;

/* Variables and functions */
 scalar_t__ SIXEL_FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIXEL_LARGE_AUTO ; 
 int /*<<< orphan*/  SIXEL_QUALITY_AUTO ; 
 int /*<<< orphan*/  SIXEL_REP_AUTO ; 
 int /*<<< orphan*/ * sixel_dither_create (int) ; 
 int /*<<< orphan*/  sixel_dither_initialize (int /*<<< orphan*/ *,unsigned char*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sixel_dither_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sixel_encode (unsigned char*,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sixel_output_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sixel_output_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sixel_write ; 
 int /*<<< orphan*/  stdout ; 

__attribute__((used)) static SIXELSTATUS output_sixel(unsigned char *pixbuf, int width, int height,
      int ncolors, int pixelformat)
{
   sixel_output_t *context;
   sixel_dither_t *dither;
   SIXELSTATUS status;

   context = sixel_output_create(sixel_write, stdout);
   dither = sixel_dither_create(ncolors);
   status = sixel_dither_initialize(dither, pixbuf,
         width, height,
         pixelformat,
         SIXEL_LARGE_AUTO,
         SIXEL_REP_AUTO,
         SIXEL_QUALITY_AUTO);
   if (SIXEL_FAILED(status))
      return status;
   status = sixel_encode(pixbuf, width, height,
         pixelformat, dither, context);
   if (SIXEL_FAILED(status))
      return status;
   sixel_output_unref(context);
   sixel_dither_unref(dither);

   return status;
}