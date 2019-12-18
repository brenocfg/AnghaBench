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

/* Variables and functions */
 int /*<<< orphan*/  _ogg_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_clear (int /*<<< orphan*/ *) ; 

int ogg_stream_destroy(ogg_stream_state *os){
  if(os){
    ogg_stream_clear(os);
    _ogg_free(os);
  }
  return(0);
}