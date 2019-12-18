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
struct ehci_iso_stream {int /*<<< orphan*/  refcount; } ;

/* Variables and functions */
 scalar_t__ likely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct ehci_iso_stream *
iso_stream_get (struct ehci_iso_stream *stream)
{
	if (likely (stream != NULL))
		stream->refcount++;
	return stream;
}