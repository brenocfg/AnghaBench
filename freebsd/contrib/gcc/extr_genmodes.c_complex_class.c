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
typedef  enum mode_class { ____Placeholder_mode_class } mode_class ;

/* Variables and functions */
 int MODE_COMPLEX_FLOAT ; 
 int MODE_COMPLEX_INT ; 
#define  MODE_FLOAT 129 
#define  MODE_INT 128 
 int MODE_RANDOM ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mode_class_names ; 

__attribute__((used)) static enum mode_class
complex_class (enum mode_class c)
{
  switch (c)
    {
    case MODE_INT: return MODE_COMPLEX_INT;
    case MODE_FLOAT: return MODE_COMPLEX_FLOAT;
    default:
      error ("no complex class for class %s", mode_class_names[c]);
      return MODE_RANDOM;
    }
}