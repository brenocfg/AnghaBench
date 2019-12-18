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
struct TYPE_3__ {scalar_t__ type; scalar_t__ keyword; } ;
typedef  TYPE_1__ c_token ;

/* Variables and functions */
 scalar_t__ CPP_KEYWORD ; 
 scalar_t__ CPP_MINUS ; 
 scalar_t__ CPP_PLUS ; 
 scalar_t__ RID_AT_OPTIONAL ; 
 scalar_t__ RID_AT_REQUIRED ; 

__attribute__((used)) static bool
c_token_starts_methodproto (c_token *token)
{
  return token->type == CPP_PLUS
    || token->type == CPP_MINUS
    || (token->type == CPP_KEYWORD
	&& (token->keyword == RID_AT_REQUIRED
	    || token->keyword == RID_AT_OPTIONAL));
}