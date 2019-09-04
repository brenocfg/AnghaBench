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
typedef  int /*<<< orphan*/  buf ;
typedef  int Int32BigEndian ;
typedef  int /*<<< orphan*/  InputStream ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  streamRead (int /*<<< orphan*/ *,unsigned char*,int) ; 

ALboolean _alutInputStreamReadInt32BE(InputStream * stream, Int32BigEndian * value)
{
  unsigned char buf[4];

  if (!streamRead(stream, buf, sizeof(buf)))
  {
    return AL_FALSE;
  }
  *value = ((Int32BigEndian) buf[0] << 24) | ((Int32BigEndian) buf[1] << 16) | ((Int32BigEndian) buf[2] << 8) | ((Int32BigEndian) buf[3]);
  return AL_TRUE;
}