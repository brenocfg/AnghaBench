#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uchar ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ val; } ;
typedef  TYPE_2__ cpp_token ;

/* Variables and functions */
 scalar_t__ CPP_NAME ; 
 int /*<<< orphan*/  NODE_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ustrcmp (int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

int
cpp_ideq (const cpp_token *token, const char *string)
{
  if (token->type != CPP_NAME)
    return 0;

  return !ustrcmp (NODE_NAME (token->val.node), (const uchar *) string);
}