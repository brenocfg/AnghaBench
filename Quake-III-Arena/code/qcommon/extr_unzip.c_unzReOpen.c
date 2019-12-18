#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * file; } ;
typedef  TYPE_1__ unz_s ;
typedef  int /*<<< orphan*/ * unzFile ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ ALLOC (int) ; 
 int /*<<< orphan*/  Com_Memcpy (TYPE_1__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * fopen (char const*,char*) ; 

extern unzFile unzReOpen (const char* path, unzFile file)
{
	unz_s *s;
	FILE * fin;

    fin=fopen(path,"rb");
	if (fin==NULL)
		return NULL;

	s=(unz_s*)ALLOC(sizeof(unz_s));
	Com_Memcpy(s, (unz_s*)file, sizeof(unz_s));

	s->file = fin;
	return (unzFile)s;	
}