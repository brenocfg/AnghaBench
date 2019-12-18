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
typedef  int uint8_t ;

/* Variables and functions */
#define  TSDB_RELATION_AND 135 
#define  TSDB_RELATION_EQUAL 134 
#define  TSDB_RELATION_LARGE 133 
#define  TSDB_RELATION_LARGE_EQUAL 132 
#define  TSDB_RELATION_LESS 131 
#define  TSDB_RELATION_LESS_EQUAL 130 
#define  TSDB_RELATION_NOT_EQUAL 129 
#define  TSDB_RELATION_OR 128 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 

__attribute__((used)) static char *tSQLOptrToString(uint8_t optr, char *dst) {
  switch (optr) {
    case TSDB_RELATION_LESS: {
      *dst = '<';
      dst += 1;
      break;
    }
    case TSDB_RELATION_LESS_EQUAL: {
      *dst = '<';
      *(dst + 1) = '=';
      dst += 2;
      break;
    }
    case TSDB_RELATION_EQUAL: {
      *dst = '=';
      dst += 1;
      break;
    }
    case TSDB_RELATION_LARGE: {
      *dst = '>';
      dst += 1;
      break;
    }
    case TSDB_RELATION_LARGE_EQUAL: {
      *dst = '>';
      *(dst + 1) = '=';
      dst += 2;
      break;
    }
    case TSDB_RELATION_NOT_EQUAL: {
      *dst = '<';
      *(dst + 1) = '>';
      dst += 2;
      break;
    }
    case TSDB_RELATION_OR: {
      memcpy(dst, "or", 2);
      dst += 2;
      break;
    }
    case TSDB_RELATION_AND: {
      memcpy(dst, "and", 3);
      dst += 3;
      break;
    }
    default:;
  }
  return dst;
}