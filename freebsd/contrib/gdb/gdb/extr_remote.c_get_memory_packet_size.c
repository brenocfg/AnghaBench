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
struct remote_state {long remote_packet_size; long actual_register_packet_size; } ;
struct memory_packet_config {long size; scalar_t__ fixed_p; } ;

/* Variables and functions */
 long MAX_REMOTE_PACKET_SIZE ; 
 long MIN_REMOTE_PACKET_SIZE ; 
 struct remote_state* get_remote_state () ; 

__attribute__((used)) static long
get_memory_packet_size (struct memory_packet_config *config)
{
  struct remote_state *rs = get_remote_state ();
  /* NOTE: The somewhat arbitrary 16k comes from the knowledge (folk
     law?) that some hosts don't cope very well with large alloca()
     calls.  Eventually the alloca() code will be replaced by calls to
     xmalloc() and make_cleanups() allowing this restriction to either
     be lifted or removed. */
#ifndef MAX_REMOTE_PACKET_SIZE
#define MAX_REMOTE_PACKET_SIZE 16384
#endif
  /* NOTE: 16 is just chosen at random. */
#ifndef MIN_REMOTE_PACKET_SIZE
#define MIN_REMOTE_PACKET_SIZE 16
#endif
  long what_they_get;
  if (config->fixed_p)
    {
      if (config->size <= 0)
	what_they_get = MAX_REMOTE_PACKET_SIZE;
      else
	what_they_get = config->size;
    }
  else
    {
      what_they_get = (rs->remote_packet_size);
      /* Limit the packet to the size specified by the user. */
      if (config->size > 0
	  && what_they_get > config->size)
	what_they_get = config->size;
      /* Limit it to the size of the targets ``g'' response. */
      if ((rs->actual_register_packet_size) > 0
	  && what_they_get > (rs->actual_register_packet_size))
	what_they_get = (rs->actual_register_packet_size);
    }
  if (what_they_get > MAX_REMOTE_PACKET_SIZE)
    what_they_get = MAX_REMOTE_PACKET_SIZE;
  if (what_they_get < MIN_REMOTE_PACKET_SIZE)
    what_they_get = MIN_REMOTE_PACKET_SIZE;
  return what_they_get;
}