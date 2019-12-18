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
#define  MODE_FLOAT 129 
#define  MODE_INT 128 
 int MODE_RANDOM ; 
 int MODE_VECTOR_FLOAT ; 
 int MODE_VECTOR_INT ; 
 int /*<<< orphan*/  error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mode_class_names ; 

__attribute__((used)) static enum mode_class
vector_class (enum mode_class cl)
{
  switch (cl)
    {
    case MODE_INT: return MODE_VECTOR_INT;
    case MODE_FLOAT: return MODE_VECTOR_FLOAT;
    default:
      error ("no vector class for class %s", mode_class_names[cl]);
      return MODE_RANDOM;
    }
}