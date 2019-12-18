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
typedef  enum debug_visibility { ____Placeholder_debug_visibility } debug_visibility ;

/* Variables and functions */
 unsigned int CXXFLAGS_VISIBILITY_PRIVATE ; 
 unsigned int CXXFLAGS_VISIBILITY_PROTECTED ; 
 unsigned int CXXFLAGS_VISIBILITY_PUBLIC ; 
#define  DEBUG_VISIBILITY_PRIVATE 130 
#define  DEBUG_VISIBILITY_PROTECTED 129 
#define  DEBUG_VISIBILITY_PUBLIC 128 
 int /*<<< orphan*/  abort () ; 

__attribute__((used)) static unsigned int
ieee_vis_to_flags (enum debug_visibility visibility)
{
  switch (visibility)
    {
    default:
      abort ();
    case DEBUG_VISIBILITY_PUBLIC:
      return CXXFLAGS_VISIBILITY_PUBLIC;
    case DEBUG_VISIBILITY_PRIVATE:
      return CXXFLAGS_VISIBILITY_PRIVATE;
    case DEBUG_VISIBILITY_PROTECTED:
      return CXXFLAGS_VISIBILITY_PROTECTED;
    }
  /*NOTREACHED*/
}