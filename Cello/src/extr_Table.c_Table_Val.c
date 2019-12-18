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
typedef  int uint64_t ;
struct Table {int ksize; scalar_t__ data; } ;
struct Header {int dummy; } ;

/* Variables and functions */
 int Table_Step (struct Table*) ; 

__attribute__((used)) static var Table_Val(struct Table* t, uint64_t i) {
  return (char*)t->data + i * Table_Step(t) +
    sizeof(uint64_t) + 
    sizeof(struct Header) + 
    t->ksize + 
    sizeof(struct Header);  
}