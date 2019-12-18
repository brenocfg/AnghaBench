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
struct type {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CHECK_TYPEDEF (struct type*) ; 
 scalar_t__ DEPRECATED_STREQ (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 int /*<<< orphan*/  TYPE_FIELD_NAME (struct type*,int /*<<< orphan*/ ) ; 
 int TYPE_NFIELDS (struct type*) ; 

int
ada_is_aligner_type (struct type *type)
{
  CHECK_TYPEDEF (type);
  return (TYPE_CODE (type) == TYPE_CODE_STRUCT
	  && TYPE_NFIELDS (type) == 1
	  && DEPRECATED_STREQ (TYPE_FIELD_NAME (type, 0), "F"));
}