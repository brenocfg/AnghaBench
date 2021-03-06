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
typedef  char* var ;
typedef  int /*<<< orphan*/  uint64_t ;
struct Table {int ksize; } ;
struct Header {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static var Table_Swapspace_Val(struct Table* t, var space) {
  return (char*)space + sizeof(uint64_t) + sizeof(struct Header) +
    t->ksize + sizeof(struct Header); 
}