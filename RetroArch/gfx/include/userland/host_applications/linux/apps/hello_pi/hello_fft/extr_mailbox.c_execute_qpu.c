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

/* Variables and functions */
 int /*<<< orphan*/  mbox_property (int,unsigned int*) ; 

unsigned execute_qpu(int file_desc, unsigned num_qpus, unsigned control, unsigned noflush, unsigned timeout) {
   int i=0;
   unsigned p[32];

   p[i++] = 0; // size
   p[i++] = 0x00000000; // process request
   p[i++] = 0x30011; // (the tag id)
   p[i++] = 16; // (size of the buffer)
   p[i++] = 16; // (size of the data)
   p[i++] = num_qpus;
   p[i++] = control;
   p[i++] = noflush;
   p[i++] = timeout; // ms

   p[i++] = 0x00000000; // end tag
   p[0] = i*sizeof *p; // actual size

   mbox_property(file_desc, p);
   return p[5];
}