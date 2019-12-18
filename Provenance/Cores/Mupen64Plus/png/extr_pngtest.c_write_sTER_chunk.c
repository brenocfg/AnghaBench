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
typedef  int /*<<< orphan*/  png_structp ;
typedef  int png_byte ;
struct TYPE_2__ {int sTER_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  STDERR ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  png_write_chunk (int /*<<< orphan*/ ,int*,int*,int) ; 
 TYPE_1__ user_chunk_data ; 
 scalar_t__ verbose ; 

__attribute__((used)) static void
write_sTER_chunk(png_structp write_ptr)
{
   png_byte sTER[5] = {115,  84,  69,  82, '\0'};

   if (verbose != 0)
      fprintf(STDERR, "\n stereo mode = %d\n", user_chunk_data.sTER_mode);

   png_write_chunk(write_ptr, sTER, &user_chunk_data.sTER_mode, 1);
}