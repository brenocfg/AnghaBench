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
typedef  int GLint ;

/* Variables and functions */
 int GL_CONTEXT_COMPATIBILITY_PROFILE_BIT ; 
 int GL_CONTEXT_CORE_PROFILE_BIT ; 
 char const* PROFILE_NAME_COMPAT ; 
 char const* PROFILE_NAME_CORE ; 

__attribute__((used)) static const char* get_profile_name_gl(GLint mask)
{
    if (mask & GL_CONTEXT_COMPATIBILITY_PROFILE_BIT)
        return PROFILE_NAME_COMPAT;
    if (mask & GL_CONTEXT_CORE_PROFILE_BIT)
        return PROFILE_NAME_CORE;

    return "unknown";
}