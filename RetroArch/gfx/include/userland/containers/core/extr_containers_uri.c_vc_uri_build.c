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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  VC_URI_PARTS_T ;

/* Variables and functions */
 int /*<<< orphan*/  build_uri (int /*<<< orphan*/  const*,char*,size_t) ; 
 size_t calculate_uri_length (int /*<<< orphan*/  const*) ; 

uint32_t vc_uri_build( const VC_URI_PARTS_T *p_uri, char *buffer, size_t buffer_size )
{
   uint32_t required_length;

   if (!p_uri)
      return 0;

   required_length = calculate_uri_length(p_uri);
   if (buffer && required_length < buffer_size)  /* Allow for NUL */
      build_uri(p_uri, buffer, buffer_size);

   return required_length;
}