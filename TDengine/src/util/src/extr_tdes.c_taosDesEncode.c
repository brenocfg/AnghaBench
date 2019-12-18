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
typedef  int /*<<< orphan*/  int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENCRYPTION_MODE ; 
 char* taosDesImp (unsigned char*,char*,int,int /*<<< orphan*/ ) ; 

char* taosDesEncode(int64_t key, char* src, int len) {
  if (len % 8 != 0) return NULL;
  unsigned char* keyStr = (unsigned char*)(&key);
  return taosDesImp(keyStr, src, len, ENCRYPTION_MODE);
}