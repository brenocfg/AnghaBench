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
typedef  int /*<<< orphan*/  word ;
typedef  int /*<<< orphan*/  byte ;
struct TYPE_3__ {scalar_t__ length; int /*<<< orphan*/  info; } ;
typedef  int /*<<< orphan*/  PLCI ;
typedef  TYPE_1__ API_PARSE ;

/* Variables and functions */
 int /*<<< orphan*/  add_ie (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void add_s(PLCI   * plci, byte code, API_PARSE * p)
{
  if(p) add_ie(plci, code, p->info, (word)p->length);
}