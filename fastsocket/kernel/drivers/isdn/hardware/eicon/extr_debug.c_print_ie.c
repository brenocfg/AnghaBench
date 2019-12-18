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
struct TYPE_3__ {int length; int* data; } ;
typedef  TYPE_1__ diva_trace_ie_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static void print_ie (diva_trace_ie_t* ie, char* buffer, int length) {
	int i;

  buffer[0] = 0;

  if (length > 32) {
    for (i = 0; ((i < ie->length) && (length > 3)); i++) {
      sprintf (buffer, "%02x", ie->data[i]);
      buffer += 2;
      length -= 2;
      if (i < (ie->length-1)) {
        strcpy (buffer, " ");
        buffer++;
        length--;
      }
    }
  }
}