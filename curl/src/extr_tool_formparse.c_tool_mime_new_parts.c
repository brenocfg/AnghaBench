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
typedef  int /*<<< orphan*/  tool_mime ;

/* Variables and functions */
 int /*<<< orphan*/  TOOLMIME_PARTS ; 
 int /*<<< orphan*/ * tool_mime_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tool_mime *tool_mime_new_parts(tool_mime *parent)
{
  return tool_mime_new(parent, TOOLMIME_PARTS);
}