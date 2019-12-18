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
typedef  TYPE_1__* WriteBuffer ;
struct TYPE_3__ {scalar_t__ used; int /*<<< orphan*/  bytes; } ;
typedef  int /*<<< orphan*/  JSON_Writer ;
typedef  int /*<<< orphan*/  JSON_Status ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_Writer_OutputBytes (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static JSON_Status WriteBuffer_Flush(WriteBuffer buffer, JSON_Writer writer)
{
   JSON_Status status = JSON_Writer_OutputBytes(writer, buffer->bytes, buffer->used);
   buffer->used = 0;
   return status;
}