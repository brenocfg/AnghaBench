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
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 int /*<<< orphan*/  DECL_TEMPLATE_INFO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_PARMS (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_TEMPLATE_SPECIALIZATION (int /*<<< orphan*/ ) ; 
 scalar_t__ TMPL_PARMS_DEPTH (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  most_general_template (int /*<<< orphan*/ ) ; 
 scalar_t__ processing_template_decl ; 

__attribute__((used)) static int
inline_needs_template_parms (tree decl)
{
  if (! DECL_TEMPLATE_INFO (decl))
    return 0;

  return (TMPL_PARMS_DEPTH (DECL_TEMPLATE_PARMS (most_general_template (decl)))
	  > (processing_template_decl + DECL_TEMPLATE_SPECIALIZATION (decl)));
}