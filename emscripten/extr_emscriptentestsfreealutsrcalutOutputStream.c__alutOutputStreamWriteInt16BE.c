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
typedef  int /*<<< orphan*/  OutputStream ;
typedef  int Int16BigEndian ;
typedef  int /*<<< orphan*/  ALboolean ;

/* Variables and functions */
 int /*<<< orphan*/  streamWrite (int /*<<< orphan*/ *,unsigned char*,int) ; 

ALboolean _alutOutputStreamWriteInt16BE(OutputStream * stream, Int16BigEndian value)
{
  unsigned char buf[2];

  buf[0] = (unsigned char)(value >> 8);
  buf[1] = (unsigned char)value;
  return streamWrite(stream, buf, 2);
}