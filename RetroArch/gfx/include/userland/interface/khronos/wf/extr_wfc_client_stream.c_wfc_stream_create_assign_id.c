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
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  WFCNativeStreamType ;

/* Variables and functions */
 scalar_t__ VCOS_EEXIST ; 
 int /*<<< orphan*/  WFC_INVALID_HANDLE ; 
 scalar_t__ wfc_stream_create (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wfc_stream_get_next () ; 

WFCNativeStreamType wfc_stream_create_assign_id(uint32_t flags)
// Create a stream, and automatically assign it a new stream number, which is returned
{
   WFCNativeStreamType stream = wfc_stream_get_next();
   uint32_t failure = wfc_stream_create(stream, flags);

   if (failure == VCOS_EEXIST)
   {
      // If a duplicate stream exists, give it one more go with a new ID
      stream = wfc_stream_get_next();
      failure = wfc_stream_create(stream, flags);
   }

   if(failure) {return WFC_INVALID_HANDLE;}
   else {return stream;}
}