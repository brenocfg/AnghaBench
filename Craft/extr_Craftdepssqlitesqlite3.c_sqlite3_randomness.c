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
 int /*<<< orphan*/  mutex ; 
 int /*<<< orphan*/  randomByte () ; 
 int /*<<< orphan*/  sqlite3_mutex_enter (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_mutex_leave (int /*<<< orphan*/ ) ; 

void sqlite3_randomness(int N, void *pBuf){
  unsigned char *zBuf = pBuf;
#if SQLITE_THREADSAFE
  sqlite3_mutex *mutex = sqlite3MutexAlloc(SQLITE_MUTEX_STATIC_PRNG);
#endif
  sqlite3_mutex_enter(mutex);
  while( N-- ){
    *(zBuf++) = randomByte();
  }
  sqlite3_mutex_leave(mutex);
}