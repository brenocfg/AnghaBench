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
typedef  int /*<<< orphan*/  u8 ;
struct av7110 {int /*<<< orphan*/  aout; } ;

/* Variables and functions */
 int /*<<< orphan*/  aux_ring_buffer_write (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dprintk (int,char*,struct av7110*) ; 

__attribute__((used)) static void play_audio_cb(u8 *buf, int count, void *priv)
{
	struct av7110 *av7110 = (struct av7110 *) priv;
	dprintk(2, "av7110:%p, \n", av7110);

	aux_ring_buffer_write(&av7110->aout, buf, count);
}