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
typedef  int /*<<< orphan*/  uivector ;
typedef  int /*<<< orphan*/  ucvector ;
struct TYPE_3__ {int /*<<< orphan*/  lazymatching; int /*<<< orphan*/  nicematch; int /*<<< orphan*/  minmatch; int /*<<< orphan*/  windowsize; scalar_t__ use_lz77; } ;
typedef  TYPE_1__ LodePNGCompressSettings ;
typedef  int /*<<< orphan*/  HuffmanTree ;
typedef  int /*<<< orphan*/  Hash ;

/* Variables and functions */
 int /*<<< orphan*/  HuffmanTree_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  HuffmanTree_getCode (int /*<<< orphan*/ *,unsigned char const) ; 
 int /*<<< orphan*/  HuffmanTree_getLength (int /*<<< orphan*/ *,unsigned char const) ; 
 int /*<<< orphan*/  HuffmanTree_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  addBitToStream (size_t*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  addHuffmanSymbol (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int encodeLZ77 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generateFixedDistanceTree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  generateFixedLitLenTree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uivector_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uivector_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeLZ77data (size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned deflateFixed(ucvector* out, size_t* bp, Hash* hash,
                             const unsigned char* data,
                             size_t datapos, size_t dataend,
                             const LodePNGCompressSettings* settings, int final)
{
  HuffmanTree tree_ll; /*tree for literal values and length codes*/
  HuffmanTree tree_d; /*tree for distance codes*/

  unsigned BFINAL = final;
  unsigned error = 0;
  size_t i;

  HuffmanTree_init(&tree_ll);
  HuffmanTree_init(&tree_d);

  generateFixedLitLenTree(&tree_ll);
  generateFixedDistanceTree(&tree_d);

  addBitToStream(bp, out, BFINAL);
  addBitToStream(bp, out, 1); /*first bit of BTYPE*/
  addBitToStream(bp, out, 0); /*second bit of BTYPE*/

  if(settings->use_lz77) /*LZ77 encoded*/
  {
    uivector lz77_encoded;
    uivector_init(&lz77_encoded);
    error = encodeLZ77(&lz77_encoded, hash, data, datapos, dataend, settings->windowsize,
                       settings->minmatch, settings->nicematch, settings->lazymatching);
    if(!error) writeLZ77data(bp, out, &lz77_encoded, &tree_ll, &tree_d);
    uivector_cleanup(&lz77_encoded);
  }
  else /*no LZ77, but still will be Huffman compressed*/
  {
    for(i = datapos; i < dataend; i++)
    {
      addHuffmanSymbol(bp, out, HuffmanTree_getCode(&tree_ll, data[i]), HuffmanTree_getLength(&tree_ll, data[i]));
    }
  }
  /*add END code*/
  if(!error) addHuffmanSymbol(bp, out, HuffmanTree_getCode(&tree_ll, 256), HuffmanTree_getLength(&tree_ll, 256));

  /*cleanup*/
  HuffmanTree_cleanup(&tree_ll);
  HuffmanTree_cleanup(&tree_d);

  return error;
}