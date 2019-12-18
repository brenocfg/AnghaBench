#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char const* scheme; } ;
typedef  TYPE_1__ VC_URI_PARTS_T ;

/* Variables and functions */

const char *vc_uri_scheme( const VC_URI_PARTS_T *p_uri )
{
   return p_uri ? p_uri->scheme : NULL;
}