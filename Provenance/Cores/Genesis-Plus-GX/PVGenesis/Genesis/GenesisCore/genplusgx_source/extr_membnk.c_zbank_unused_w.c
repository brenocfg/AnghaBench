void zbank_unused_w(unsigned int address, unsigned int data)
{
#ifdef LOGERROR
  error("Z80 bank unused write %06X = %02X (%x)\n", address, data, Z80.pc.d);
#endif
}