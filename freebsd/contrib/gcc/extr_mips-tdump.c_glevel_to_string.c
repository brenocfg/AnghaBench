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
typedef  int glevel_t ;

/* Variables and functions */
#define  GLEVEL_0 131 
#define  GLEVEL_1 130 
#define  GLEVEL_2 129 
#define  GLEVEL_3 128 

__attribute__((used)) static const char *
glevel_to_string (glevel_t g_level)
{
  switch(g_level)
    {
    case GLEVEL_0: return "G0";
    case GLEVEL_1: return "G1";
    case GLEVEL_2: return "G2";
    case GLEVEL_3: return "G3";
    }

  return "??";
}