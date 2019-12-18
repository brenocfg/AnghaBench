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
typedef  struct String* var ;
typedef  int /*<<< orphan*/  uint64_t ;
struct String {int /*<<< orphan*/  val; } ;

/* Variables and functions */
 int /*<<< orphan*/  hash_data (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t String_Hash(var self) {
  struct String* s = self;
  return hash_data(s->val, strlen(s->val));
}