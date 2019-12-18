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
typedef  enum pcm037_board_variant { ____Placeholder_pcm037_board_variant } pcm037_board_variant ;

/* Variables and functions */
 int pcm037_instance ; 

enum pcm037_board_variant pcm037_variant(void)
{
	return pcm037_instance;
}