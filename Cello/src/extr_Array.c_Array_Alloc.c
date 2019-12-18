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
struct Header {int dummy; } ;
struct Array {int /*<<< orphan*/  type; scalar_t__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  AllocData ; 
 size_t Array_Step (struct Array*) ; 
 int /*<<< orphan*/  header_init (struct Header*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void Array_Alloc(struct Array* a, size_t i) {
  memset((char*)a->data + Array_Step(a) * i, 0, Array_Step(a));
  struct Header* head = (struct Header*)((char*)a->data + Array_Step(a) * i);
  header_init(head, a->type, AllocData);
}