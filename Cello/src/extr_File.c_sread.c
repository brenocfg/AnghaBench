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
typedef  int /*<<< orphan*/  var ;

/* Variables and functions */
 int /*<<< orphan*/  Stream ; 
 size_t method (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t (*) (int /*<<< orphan*/ ,void*,size_t),void*,size_t) ; 

size_t sread(var self, void* output, size_t size) {
  return method(self, Stream, sread, output, size);
}