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
 int /*<<< orphan*/  compact_writer ; 
 int /*<<< orphan*/  csv_writer ; 
 int /*<<< orphan*/  default_writer ; 
 int /*<<< orphan*/  flat_writer ; 
 int /*<<< orphan*/  ini_writer ; 
 int /*<<< orphan*/  json_writer ; 
 int /*<<< orphan*/  writer_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xml_writer ; 

__attribute__((used)) static void writer_register_all(void)
{
    static int initialized;

    if (initialized)
        return;
    initialized = 1;

    writer_register(&default_writer);
    writer_register(&compact_writer);
    writer_register(&csv_writer);
    writer_register(&flat_writer);
    writer_register(&ini_writer);
    writer_register(&json_writer);
    writer_register(&xml_writer);
}