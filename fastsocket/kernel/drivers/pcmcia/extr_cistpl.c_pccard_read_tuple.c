#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int TupleDataMax; scalar_t__ TupleOffset; int /*<<< orphan*/ * TupleData; scalar_t__ Attributes; int /*<<< orphan*/  DesiredTuple; } ;
typedef  TYPE_1__ tuple_t ;
struct pcmcia_socket {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  cisdata_t ;

/* Variables and functions */
 unsigned int BIND_FN_ALL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 scalar_t__ TUPLE_RETURN_COMMON ; 
 int /*<<< orphan*/  dev_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * kmalloc (int,int /*<<< orphan*/ ) ; 
 int pccard_get_first_tuple (struct pcmcia_socket*,unsigned int,TYPE_1__*) ; 
 int pccard_get_tuple_data (struct pcmcia_socket*,TYPE_1__*) ; 
 int pcmcia_parse_tuple (TYPE_1__*,void*) ; 

int pccard_read_tuple(struct pcmcia_socket *s, unsigned int function, cisdata_t code, void *parse)
{
    tuple_t tuple;
    cisdata_t *buf;
    int ret;

    buf = kmalloc(256, GFP_KERNEL);
    if (buf == NULL) {
	    dev_printk(KERN_WARNING, &s->dev, "no memory to read tuple\n");
	    return -ENOMEM;
    }
    tuple.DesiredTuple = code;
    tuple.Attributes = 0;
    if (function == BIND_FN_ALL)
	    tuple.Attributes = TUPLE_RETURN_COMMON;
    ret = pccard_get_first_tuple(s, function, &tuple);
    if (ret != 0)
	    goto done;
    tuple.TupleData = buf;
    tuple.TupleOffset = 0;
    tuple.TupleDataMax = 255;
    ret = pccard_get_tuple_data(s, &tuple);
    if (ret != 0)
	    goto done;
    ret = pcmcia_parse_tuple(&tuple, parse);
done:
    kfree(buf);
    return ret;
}