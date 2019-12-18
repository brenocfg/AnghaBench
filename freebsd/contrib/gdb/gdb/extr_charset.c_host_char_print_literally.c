#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int (* host_char_print_literally ) (int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  host_char_print_literally_baton; } ;

/* Variables and functions */
 TYPE_1__* current_host_charset ; 
 int stub1 (int /*<<< orphan*/ ,int) ; 

int
host_char_print_literally (int host_char)
{
  return ((*current_host_charset->host_char_print_literally)
          (current_host_charset->host_char_print_literally_baton,
           host_char));
}