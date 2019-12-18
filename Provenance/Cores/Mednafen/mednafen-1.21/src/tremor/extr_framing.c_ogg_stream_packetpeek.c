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
typedef  int /*<<< orphan*/  ogg_packet ;

/* Variables and functions */
 int _packetout (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ ogg_stream_check (int /*<<< orphan*/ *) ; 

int ogg_stream_packetpeek(ogg_stream_state *os,ogg_packet *op){
  if(ogg_stream_check(os)) return 0;
  return _packetout(os,op,0);
}