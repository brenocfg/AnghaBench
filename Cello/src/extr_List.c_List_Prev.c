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
typedef  scalar_t__ var ;
struct List {int dummy; } ;
struct Header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static var* List_Prev(struct List* l, var self) {
  return (var*)((char*)self - sizeof(struct Header) - 2 * sizeof(var));
}