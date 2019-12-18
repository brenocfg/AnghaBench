#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {char* name; int /*<<< orphan*/  next; int /*<<< orphan*/  key_size; } ;
typedef  TYPE_1__ libretrodb_index_t ;
typedef  int /*<<< orphan*/  RFILE ;

/* Variables and functions */
 scalar_t__ STRLEN_CONST (char*) ; 
 int /*<<< orphan*/  rmsgpack_write_map_header (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rmsgpack_write_string (int /*<<< orphan*/ *,char*,scalar_t__) ; 
 int /*<<< orphan*/  rmsgpack_write_uint (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char*) ; 

__attribute__((used)) static void libretrodb_write_index_header(RFILE *fd, libretrodb_index_t *idx)
{
   rmsgpack_write_map_header(fd, 3);
   rmsgpack_write_string(fd, "name", STRLEN_CONST("name"));
   rmsgpack_write_string(fd, idx->name, (uint32_t)strlen(idx->name));
   rmsgpack_write_string(fd, "key_size", (uint32_t)STRLEN_CONST("key_size"));
   rmsgpack_write_uint(fd, idx->key_size);
   rmsgpack_write_string(fd, "next", STRLEN_CONST("next"));
   rmsgpack_write_uint(fd, idx->next);
}