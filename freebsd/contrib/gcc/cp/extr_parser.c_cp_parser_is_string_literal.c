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
struct TYPE_3__ {scalar_t__ type; } ;
typedef  TYPE_1__ cp_token ;

/* Variables and functions */
 scalar_t__ CPP_STRING ; 
 scalar_t__ CPP_WSTRING ; 

__attribute__((used)) static bool
cp_parser_is_string_literal (cp_token* token)
{
  return (token->type == CPP_STRING || token->type == CPP_WSTRING);
}