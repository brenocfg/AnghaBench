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
typedef  long int64_t ;
typedef  int int32_t ;

/* Variables and functions */
 long MILLISECOND_PER_DAY ; 
 long MILLISECOND_PER_HOUR ; 
 long MILLISECOND_PER_MINUTE ; 
 long MILLISECOND_PER_MONTH ; 
 long MILLISECOND_PER_SECOND ; 
 long MILLISECOND_PER_WEEK ; 
 long MILLISECOND_PER_YEAR ; 

__attribute__((used)) static int32_t getTimestampInUsFromStrImpl(int64_t val, char unit, int64_t* result) {
  *result = val;

  switch (unit) {
    case 's':
      (*result) *= MILLISECOND_PER_SECOND;
      break;
    case 'm':
      (*result) *= MILLISECOND_PER_MINUTE;
      break;
    case 'h':
      (*result) *= MILLISECOND_PER_HOUR;
      break;
    case 'd':
      (*result) *= MILLISECOND_PER_DAY;
      break;
    case 'w':
      (*result) *= MILLISECOND_PER_WEEK;
      break;
    case 'n':
      (*result) *= MILLISECOND_PER_MONTH;
      break;
    case 'y':
      (*result) *= MILLISECOND_PER_YEAR;
      break;
    case 'a':
      break;
    default: {
      ;
      return -1;
    }
  }

  /* get the value in microsecond */
  (*result) *= 1000L;
  return 0;
}