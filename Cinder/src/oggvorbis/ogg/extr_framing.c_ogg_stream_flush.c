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
typedef  int /*<<< orphan*/  ogg_stream_state ;
typedef  int /*<<< orphan*/  ogg_page ;

/* Variables and functions */
 int ogg_stream_flush_i (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

int ogg_stream_flush(ogg_stream_state *os,ogg_page *og){
  return ogg_stream_flush_i(os,og,1,4096);
}