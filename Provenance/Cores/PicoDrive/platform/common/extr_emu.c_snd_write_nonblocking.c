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

/* Variables and functions */
 int /*<<< orphan*/  PsndOut ; 
 int /*<<< orphan*/  sndout_write_nb (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void snd_write_nonblocking(int len)
{
	sndout_write_nb(PsndOut, len);
}