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
typedef  int /*<<< orphan*/  outf_p ;

/* Variables and functions */
 int NUM_RTX_CODE ; 
 int /*<<< orphan*/  get_output_file_with_visibility (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  oprintf (int /*<<< orphan*/ ,char*,...) ; 
 int* rtx_next_new ; 

__attribute__((used)) static void
write_rtx_next (void)
{
  outf_p f = get_output_file_with_visibility (NULL);
  int i;

  oprintf (f, "\n/* Used to implement the RTX_NEXT macro.  */\n");
  oprintf (f, "const unsigned char rtx_next[NUM_RTX_CODE] = {\n");
  for (i = 0; i < NUM_RTX_CODE; i++)
    if (rtx_next_new[i] == -1)
      oprintf (f, "  0,\n");
    else
      oprintf (f,
	       "  RTX_HDR_SIZE + %d * sizeof (rtunion),\n",
	       rtx_next_new[i]);
  oprintf (f, "};\n");
}