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
typedef  int UInt16LittleEndian ;
typedef  int /*<<< orphan*/  InputStream ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  AL_FALSE ; 
 int /*<<< orphan*/  AL_TRUE ; 
 int /*<<< orphan*/  streamRead (int /*<<< orphan*/ *,unsigned char*,int) ; 

ALboolean _alutInputStreamReadUInt16LE(InputStream * stream, UInt16LittleEndian * value)
{
  unsigned char buf[2];

  if (!streamRead(stream, buf, sizeof(buf)))
  {
    return AL_FALSE;
  }
  *value = ((UInt16LittleEndian) buf[1] << 8) | ((UInt16LittleEndian) buf[0]);
  return AL_TRUE;
}