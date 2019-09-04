#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {char const* data; } ;
typedef  TYPE_1__ tool_mime ;

/* Variables and functions */
 int /*<<< orphan*/  CONST_FREE (char const*) ; 
 int /*<<< orphan*/  TOOLMIME_DATA ; 
 char* strdup (char const*) ; 
 TYPE_1__* tool_mime_new (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static tool_mime *tool_mime_new_data(tool_mime *parent, const char *data)
{
  tool_mime *m = NULL;

  data = strdup(data);
  if(data) {
    m = tool_mime_new(parent, TOOLMIME_DATA);
    if(!m)
      CONST_FREE(data);
    else
      m->data = data;
  }
  return m;
}