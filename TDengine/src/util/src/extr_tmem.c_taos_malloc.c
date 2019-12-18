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
 int isMallocMem (unsigned int,char*) ; 
 void* malloc (unsigned int) ; 

void* taos_malloc(unsigned int size, char* _func) {

  if (false == isMallocMem(size, _func)) {    
    return NULL;
  }
  
  void *p = NULL;    
  p = malloc(size); 
  return p;
}