#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  path; } ;
typedef  TYPE_1__ VC_URI_PARTS_T ;

/* Variables and functions */
 int duplicate_string (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_uri_set_path_extension (TYPE_1__*) ; 

bool vc_uri_set_path( VC_URI_PARTS_T *p_uri, const char *path )
{
   bool ret = p_uri ? duplicate_string(path, &p_uri->path) : false;
   vc_uri_set_path_extension(p_uri);
   return ret;
}